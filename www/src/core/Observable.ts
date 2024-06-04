export type Observer<T> = (data: T) => void

export class Observable<T> {
  private observers: Observer<T>[] = [];

  public subscribe(observer: Observer<T>) {
    this.observers.push(observer);
  }

  public unsubscribe(observer: Observer<T>) {
    this.observers = this.observers.filter((it) => it !== observer);
  }

  public notify(data: T) {
    this.observers.forEach((observer) => observer(data));
  }
}
