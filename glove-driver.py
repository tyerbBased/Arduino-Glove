import time
import serial
import serial.tools.list_ports
from pynput.mouse import Controller, Button

# --- MOUSE CONTROLLER ---
class MouseController:
    def __init__(self):
        self.mouse = Controller()
            
    def move(self, dx, dy):
        if dx == 0 and dy == 0:
            return
        self.mouse.move(dx, dy)
            
    def scroll(self, amount):
        if amount == 0:
            return
        self.mouse.scroll(0, amount)

    def press_left(self):
        self.mouse.press(Button.left)

    def release_left(self):
        self.mouse.release(Button.left)

    def press_right(self):
        self.mouse.press(Button.right)

    def release_right(self):
        self.mouse.release(Button.right)

# --- CONFIGURATION (Edit these values) ---
BAUD = 115200

DEADZONE = 1000              # Minimum gyro value to trigger movement
SENSITIVITY = 150.0          # Lower = faster mouse movement
SCROLL_SENSITIVITY = 500.0   # Lower = faster scrolling

def find_arduino():
    """Auto-detect Arduino by scanning all connected serial devices"""
    ports = serial.tools.list_ports.comports()
    
    if not ports:
        return None
    
    for p in ports:
        if p.manufacturer and 'Arduino' in p.manufacturer:
            return p.device, p.vid, p.pid
        # Fallback: detect common CH340 USB-to-Serial chips used in Arduino clones
        if p.vid and p.pid:
            if (p.vid, p.pid) in [(0x1a86, 0x7523), (0x2341, 0x0043), (0x2341, 0x0243)]:
                return p.device, p.vid, p.pid
    
    return None

def run_mouse_loop(ser, mouse):
    """Main control loop"""
    left_down = False
    right_down = False

    while True:
        try:
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8', errors='ignore').strip()
                if not line:
                    continue

                try:
                    gyX, gyY, gyZ, b1, b2, b3 = map(int, line.split(','))
                except ValueError:
                    continue

                disable_move = (b1 == 0)
                lmb = (b2 == 0)
                rmb = (b3 == 0)
                scroll_mode = (disable_move and rmb)

                dx = int(-(gyZ / SENSITIVITY)) if abs(gyZ) > DEADZONE else 0
                dy = int((gyX / SENSITIVITY)) if abs(gyX) > DEADZONE else 0

                if scroll_mode:
                    if abs(gyX) > DEADZONE:
                        scroll_amount = int(-(gyX / SCROLL_SENSITIVITY))
                        mouse.scroll(scroll_amount)
                    
                    if left_down: 
                        mouse.release_left()
                        left_down = False
                    if right_down: 
                        mouse.release_right()
                        right_down = False
                    
                else:
                    if not disable_move:
                        mouse.move(dx, dy)

                    if lmb and not left_down:
                        mouse.press_left()
                        left_down = True
                    elif not lmb and left_down:
                        mouse.release_left()
                        left_down = False

                    if rmb and not right_down and not disable_move:
                        mouse.press_right()
                        right_down = True
                    elif not rmb and right_down:
                        mouse.release_right()
                        right_down = False

            time.sleep(0.001)

        except (serial.SerialException, OSError):
            print('[!] Arduino disconnected')
            break 

def main():
    mouse = MouseController()
    print('[*] Backend: pynput')
    print('[*] Searching for Arduino...\n')

    while True:
        result = find_arduino()
        
        if result:
            port, vid, pid = result
            print(f'[+] Arduino found: {port} (VID: 0x{vid:04x}, PID: 0x{pid:04x})')
            print(f'[+] Connecting at {BAUD} baud...')
            
            try:
                ser = serial.Serial(port, BAUD, timeout=0.1)
                print('[+] Connected! Listening for gyro data...\n')
                run_mouse_loop(ser, mouse)
                ser.close()
            except (serial.SerialException, OSError) as e:
                print(f'[!] Connection failed: {e}')
                time.sleep(2)
        else:
            print('[*] No Arduino detected. Waiting...')
            time.sleep(2)

if __name__ == '__main__':
    main()
