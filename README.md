# WeatherStation

![stability-wip](https://img.shields.io/badge/Stability-WIP-lightgrey.svg)

WIP: more detailed description will be added later.

## Dependencies

After cloning, you need to execute the following command
in order to download all the dependencies:

```bash
git submodule update --init --recursive
```

## Configuration

The app will connect to your Wi-Fi network, so you should
provide network's credentials by creating `credentials.json`
file with the following content:

```json
{
  "ssid": "<network name>",
  "passwd": "<password>"
}
```

> [!IMPORTANT]
> Most ESP32 board won't be able to connect to 5GHz network.
> So you should make sure you are connecting to the 2.4GHz network.

## Building

First of all, change working directory to `scripts`:

```bash
cd scripts
```

### Web UI

Make sure you have `npm` installed. Tested with `npm 10.5.0`.

1. Make the script executable
   ```bash
   chmod +x www.sh
   ```
2. Install dependencies
   ```bash
   ./www.sh init
   ```
3. Build
   ```bash
   ./www.sh build
   ```
4. And, finally, flash it to the board
   ```bash
   ./www.sh flash
   ```

> [!TIP]
> You can perform all three actions at once:
> ```bash
> ./www.sh init build flash
> ```

### Backend

1. Make the script executable
   ```bash
   chmod +x ws.sh
   ```
2. In order to run (i.e., build and monitor), execute
   ```bash
   ./ws.sh run
   ```
