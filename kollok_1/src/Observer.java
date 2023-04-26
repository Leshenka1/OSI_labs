// Интерфейс наблюдателя (уведомителя)
interface Observer {
    String receivedMessage = null;
    void update(String message);

    default String getReceivedMessage(){
        return receivedMessage;
    }
}
