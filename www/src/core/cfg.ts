export class cfg {
  private static _baseUrl: string | undefined = process.env.REACT_APP_WS_BASE_URL;

  public static get baseUrl() {
    return this._baseUrl === undefined ? "" : this._baseUrl;
  }
}
