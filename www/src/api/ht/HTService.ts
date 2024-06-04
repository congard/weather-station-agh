import {HTRecord} from "./HTRecord";
import {cfg} from "../../core/cfg";

type CurrentStateResponse = {
  humidity: number;
  temperature: number;
  updateFrequency: number;
}

type SuccessCallback<T> = (record: T) => void;
type ErrorCallback = (error: Error) => void;

export class HTService {
  public getCurrent(
    onSuccess: SuccessCallback<HTRecord>,
    onError: ErrorCallback
  ) {
    this.readSensor(
      curr => onSuccess(new HTRecord(curr.humidity, curr.temperature, new Date())),
      onError);
  }

  public readSensor(
    onSuccess: SuccessCallback<CurrentStateResponse>,
    onError: ErrorCallback
  ) {
    fetch(`${cfg.baseUrl}/api/sensors/dht22`)
      .then(r => r.json())
      .then(r => {
        const curr = r as CurrentStateResponse
        onSuccess(curr)
      }).catch(error => onError(error));
  }

  public getLast(
    count: number,
    onSuccess: SuccessCallback<HTRecord[]>,
    onError: ErrorCallback
  ) {
    // TODO
  }

  public getPeriod(
    range: { from?: number; to?: number },
    onSuccess: SuccessCallback<HTRecord[]>,
    onError: ErrorCallback
  ) {
    // TODO
  }
}
