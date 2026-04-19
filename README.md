<h1>wiring of ESP32 (FC)</h1>
<img width="1538" height="550" alt="grafik" src="https://github.com/user-attachments/assets/af10fbf5-8ba7-4a84-a89e-b030e5e377b4" />
<ul>
  <li>GPIO1-GPIO4 -> motor 1-4 connection with the ESC</li>
  <li>GPIO5 -> SDA of MS5611</li>
  <li>GPIO6 -> SCL of MS5611</li>
  <li>GPIO7 -> SCL of IMU</li>
  <li>GPIO8 -> AD0 of IMU</li>
  <li>GPIO9 -> SDA of IMU</li>
  <li>GPIO43 -> convert TX to RX via software, connect telemetry output of the ESC to this pin</li>
  <li>GPIO44 -> NCS of IMU</li>
</ul>



