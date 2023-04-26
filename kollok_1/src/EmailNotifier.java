// Конкретный наблюдатель (уведомитель) по Email
class EmailNotifier implements Observer {
    private String receivedMessage;
    @Override
    public void update(String message) {
        System.out.println("Отправка уведомления по Email: " + message);
        receivedMessage = "Отправка уведомления по Email: " + message;
    }

    public String getReceivedMessage() {
        return receivedMessage;
    }
}