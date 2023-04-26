// Главный класс программы
public class Main {
    public static void main(String[] args) {
        // Создание объектов наблюдателей (уведомителей)
        Observer emailNotifier = new EmailNotifier();
        Observer smsNotifier = new SmsNotifier();

        // Создание объекта декоратора (логирования) и передача ему наблюдателя по Email
        Observer loggingDecorator = new LoggingDecorator(emailNotifier);

        // Создание объекта субъекта (сервиса уведомлений)
        Subject notificationService = new NotificationService();

        // Подключение наблюдателей (уведомителей) к сервису уведомлений
        notificationService.attach(emailNotifier);
        notificationService.attach(smsNotifier);

        // Отправка уведомления
        notificationService.notifyObservers("Новое уведомление!");

        // Отправка уведомления с декоратором (логированием)
        notificationService.attach(loggingDecorator);
        notificationService.notifyObservers("Уведомление с логированием");

        // Отсоединение декоратора (логирования) от сервиса уведомлений
        notificationService.detach(loggingDecorator);

        // Отправка уведомления без декоратора (логирования)
        notificationService.notifyObservers("Еще одно уведомление без логирования");

        // Отсоединение всех наблюдателей (уведомителей) от сервиса уведомлений
        notificationService.detach(emailNotifier);
        notificationService.detach(smsNotifier);

        // Попытка отправки уведомления после отсоединения всех наблюдателей (уведомителей)
        notificationService.notifyObservers("Уведомление после отсоединения всех уведомителей");
    }
}