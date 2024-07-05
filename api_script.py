
import tkinter as tk
from tkinter import ttk, messagebox
import serial
import serial.tools.list_ports

class ThinkerApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Thinker API for ESP32")

        self.create_widgets()
        self.populate_serial_ports()

    def create_widgets(self):
        self.port_label = tk.Label(self.root, text="Select COM Port:")
        self.port_label.pack(pady=5)

        self.port_combobox = ttk.Combobox(self.root, state="readonly")
        self.port_combobox.pack(pady=5)

        self.command_label = tk.Label(self.root, text="Enter Command:")
        self.command_label.pack(pady=5)

        self.command_entry = tk.Entry(self.root)
        self.command_entry.pack(pady=5)

        self.send_button = tk.Button(self.root, text="Send Command", command=self.send_command)
        self.send_button.pack(pady=5)

        self.response_label = tk.Label(self.root, text="Response:")
        self.response_label.pack(pady=5)

        self.response_text = tk.Text(self.root, height=10, width=50)
        self.response_text.pack(pady=5)

    def populate_serial_ports(self):
        ports = self.list_serial_ports()
        self.port_combobox['values'] = ports
        if ports:
            self.port_combobox.current(0)

    def list_serial_ports(self):
        return [port.device for port in serial.tools.list_ports.comports()]

    def send_command(self):
        port = self.port_combobox.get()
        command = self.command_entry.get()

        if not port:
            messagebox.showerror("Error", "Please select a COM port.")
            return

        if not command:
            messagebox.showerror("Error", "Please enter a command.")
            return

        response = self.send_command_to_esp32(port, command)
        self.response_text.insert(tk.END, f"Command: {command}\nResponse: {response}\n\n")

    def send_command_to_esp32(self, port, command):
        try:
            ser = serial.Serial(port, 115200, timeout=1, rtscts=False)
            ser.write(command.encode())
            response = ser.read(1000).decode()  # Read up to 100 bytes
            ser.close()
            return response
        except serial.SerialException as e:
            return f"Error communicating with the ESP32: {e}"

if __name__ == "__main__":
    root = tk.Tk()
    app = ThinkerApp(root)
    root.mainloop()