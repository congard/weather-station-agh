import {Observable} from "../../core/Observable";
import {HTRecord} from "./HTRecord";
import {HTService} from "./HTService";
import {LocalConfig} from "../../core/LocalConfig";

export class HTFetcher {
  private _recordsObservable = new Observable<HTRecord[]>();
  private _errorObservable = new Observable<Error>();

  private htService: HTService;
  private config: LocalConfig;

  private isRunning: boolean = true;

  private _fetchedRecords = new Array<HTRecord>();

  public constructor(htService: HTService, config: LocalConfig) {
    this.htService = htService;
    this.config = config;
  }

  public start() {
    this.isRunning = true;

    const intervalId = setInterval(() => {
      this.htService.getCurrent(
        record => this.onFetch(record),
        error => this._errorObservable.notify(error));

      if (!this.isRunning) {
        clearInterval(intervalId)
      }
    }, this.config.updateDelay)
  }

  public stop() {
    this.isRunning = false;
  }

  public get recordsObservable() {
    return this._recordsObservable;
  }

  public get errorObservable() {
    return this._errorObservable;
  }

  public get fetchedRecords() {
    return this._fetchedRecords;
  }

  private onFetch(record: HTRecord) {
    const n = this._fetchedRecords.length
    const maxCount = this.config.maxRecordCount

    if (n >= maxCount)
      this._fetchedRecords = this._fetchedRecords.slice(maxCount - n + 1);

    this._fetchedRecords.push(record)

    this._recordsObservable.notify(this._fetchedRecords)
  }
}
