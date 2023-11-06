import serial.tools.list_ports
import time
import subprocess

def list_available_ports():
    ports = serial.tools.list_ports.comports()
    if not ports:
        print("No COM ports available.")
    else:
        print("Available COM ports:")
        for index, port in enumerate(ports, start=1):
            print(f"{index}: {port.device}")

def select_port():
    while True:
        list_available_ports()
        choice = input("Select a COM port (e.g., 1): ")
        try:
            choice = int(choice)
            if 1 <= choice <= len(serial.tools.list_ports.comports()):
                selected_port = list(serial.tools.list_ports.comports())[choice - 1].device
                return selected_port
            else:
                print("Invalid choice. Please select a valid COM port number.")
        except ValueError:
            print("Invalid input. Please enter a number.")

def send_data(data): 
    """Send data bytes over the serial connection with a progress bar."""
    total_bytes = len(data)
    bytes_sent = 0
    print("Sending data:")
    while bytes_sent < total_bytes:
        try:
            bytes_to_send = min(100, total_bytes - bytes_sent)  # Send 10 bytes at a time (adjust as needed)
            ser.write(data[bytes_sent:bytes_sent + bytes_to_send])
            bytes_sent += bytes_to_send
            progress = int(40 * bytes_sent / total_bytes)  # Calculate progress as a percentage
            progress_bar = "[" + "#" * progress + " " * (40 - progress) + "]"
            print(f"\r{progress_bar} {bytes_sent}/{total_bytes} bytes sent", end='', flush=True)
            time.sleep(0.1)  # Add a small delay to control the update speed of the progress bar           
        except serial.SerialException as e:
            print(f"Error: {e}")
    print("\nData sent successfully. Length: {0} bytes".format(total_bytes))

    

def open_file_for_pasting(file_path):
    """Open the file for the user to paste data."""
    try:
        os.system(f'start notepad.exe {file_path}')  # Open with Notepad (Windows)
    except Exception as e:
        print(f"Error opening file: {e}")


def create_and_open_file(file_path):
    """Create a new file or open an existing one for writing."""
    try:
        with open(file_path, 'w'):
            pass
        print(f"File created: {file_path}")
        subprocess.Popen(['notepad.exe', file_path], shell=True).wait()  # Open with Notepad (Windows)
    except IOError as e:
        print(f"Error creating file: {e}")
    return file_path


def get_user_input():
    """Read data from a text file and return it as a string."""
    
    create_and_open_file('data.txt')
    try:
        with open('data.txt', 'r') as file:
            data = file.read()
    except FileNotFoundError:
            print(f"File not found: {'data.txt'}")

   # Remove newlines and whitespace
    user_input = data.replace('\n', '').replace('\r', '').replace(' ', '')

    # Extract the data portion between '{' and '}' and split it into hex values
    data_str = user_input.split('{')[1].split('}')[0]
    hex_values = [int(value.strip(), 16) for value in data_str.split(',') if '0x' in value]
    
    # Convert the hex values to bytes
    data_bytes = bytes(hex_values)

    # Calculate and print the length of the received data
    print(f"array size : {len(data_bytes)} bytes")

    return data_bytes

if __name__ == "__main__":
    while(True):
        selected_port = select_port()
        print(f"Selected COM port: {selected_port}")
        ser = serial.Serial(selected_port , 115200)
        data_to_send  = get_user_input()
        CMD_START = bytes([0x13])
        send_data(CMD_START)
        #wait till it responds
        ser.read_until(b"ok")
        len_bytes = len(data_to_send).to_bytes((len(data_to_send).bit_length() + 7) // 8, byteorder='little')
        send_data(len_bytes)
        send_data(data_to_send)
        print("\n================================================")
        print("##################### Done #####################")
        print("================================================\n")
        ser.close()
    # You can use the 'selected_port' variable for further communication.
