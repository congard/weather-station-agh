# WeatherStation

![stability-wip](https://img.shields.io/badge/Stability-WIP-lightgrey.svg)

WIP: more detailed description will be added later.

## Dependencies

After cloning, you need to execute the following command
in order to download all the dependencies:

```bash
git submodule update --init --recursive
```

## Useful commands

```bash
# monitor
pio device monitor

# upload
pio run -t upload

# upload + monitor
pio run -t upload -t monitor
```
