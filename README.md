<h1>materials</h1>
<ul>
  <li>flight controller: XIAO ESP32 S3</li>
  <li>controller: another XIAO ESP32 S3</li>
  <li>IMU: MPU6500</li>
  <li>barometer: MS5611</li>
  <li>ESC: Sequre Blueson A2 (comes with power cables, XT60 connector and capacitor)</li>
  <li>motors: iFlight XING-E Pro 2207 2450KV (screws and self-locking nuts included)</li>
  <li>props: iFlight Nazgul F5
  <li>battery: Goldbat 4s 1500mAh Lipo</li>
  <li>generic DC-DC 3A adjustable buck converter</li>
  <li>2.4GHz rod antenna (2.81dBi) for Seeed Studio XIAO x2</li>
  <li>M3 screw set with nuts and screwdriver/ratchet wrench</li>
  <li>M3 silicon shock absorber rings</li>
  <li>3D printer for the frame (Elegoo Neptune 4) and white&black Elegoo Pla+</li>
  <li>soldering equipment: 
    <ul> 
      <li>900M-T-I soldering tips recommend when working with the ESP32&sensors</li>
      <li>brass wool for cleaning</li>
      <li>tip re-tiner
    </ul>
  </li>
  <li>multimeter</li>
  <li>high AWG cables</li>
</ul>

<h1>wiring of ESP32 (FC)</h1>

<ul>
  <li>GPIO1-GPIO4 -> motor 1-4 connection with the ESC</li>
  <li>SDA -> SDA of MS5611</li>
  <li>SCL -> SCL of MS5611</li>
  <li>GPIO43 (TX) -> convert TX to RX via software, connect telemetry output of the ESC to this pin</li>
  <li>MOSI -> SDA of IMU</li>
  <li>MISO -> AD0 of IMU</li>
  <li>SCK -> SCL of IMU</li>
  <li>GPIO44 (RX) -> NCS of IMU</li>
</ul>



