// Конкретный наблюдатель (уведомитель) по SMS
class SmsNotifier implements Observer {
    private String receivedMessage;
    @Override
    public void update(String message) {
        System.out.println("Отправка уведомления по SMS: " + message);
        receivedMessage = "Отправка уведомления по SMS: " + message;
    }

    public String getReceivedMessage() {
        return receivedMessage;
    }
}