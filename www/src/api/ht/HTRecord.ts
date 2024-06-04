export class HTRecord {
  public humidity: number;
  public temperature: number;
  public timestamp: Date;

  public constructor(humidity: number, temperature: number, timestamp: Date) {
    this.humidity = humidity;
    this.temperature = temperature;
    this.timestamp = timestamp;
  }
}
