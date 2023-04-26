// Декоратор (логирования) для наблюдателей (уведомителей)
class LoggingDecorator implements Observer {
    private Observer decoratedObserver;
    private String receivedMessage;

    public LoggingDecorator(Observer decoratedObserver) {
        this.decoratedObserver = decoratedObserver;
        receivedMessage = decoratedObserver.getReceivedMessage();
    }

    @Override
    public void update(String message) {
        System.out.println("Логирование: " + message);
        receivedMessage = "Логирование: " +  message;
        decoratedObserver.update(receivedMessage);
    }

    public String getReceivedMessage() {
        return this.decoratedObserver.getReceivedMessage();
    }
}
