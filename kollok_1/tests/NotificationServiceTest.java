// Unit-тесты для классов
import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;
//import static org.mockito.Mockito.*;
public class NotificationServiceTest {
    private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
    private final PrintStream originalOut = System.out;

    @Before
    public void setUpStreams() {
        System.setOut(new PrintStream(outContent));
    }

    @After
    public void restoreStreams() {
        System.setOut(originalOut);
    }

    @Test
    public void testNotificationService() {
        // Создание объектов наблюдателей (уведомителей)
        Observer emailNotifier = new EmailNotifier();
        Observer smsNotifier = new SmsNotifier();

        // Создание объекта субъекта (сервиса уведомлений)
        Subject notificationService = new NotificationService();

        // Подключение наблюдателей (уведомителей) к сервису уведомлений
        notificationService.attach(emailNotifier);
        notificationService.attach(smsNotifier);

        // Отправка уведомления
        notificationService.notifyObservers("Новое сообщение: тестовое уведомление");

        // Проверка, что уведомления были отправлены
        assertEquals("Отправка уведомления по Email: Новое сообщение: тестовое уведомление",
                ((EmailNotifier) emailNotifier).getReceivedMessage());
        assertEquals("Отправка уведомления по SMS: Новое сообщение: тестовое уведомление",
                ((SmsNotifier) smsNotifier).getReceivedMessage());

        }

    @Test
    public void testNotificationServiceWithLogging() {
        // Создание объектов наблюдателей (уведомителей)
        Observer emailNotifierForLogging = new EmailNotifier();
        Observer smsNotifierForLogging = new SmsNotifier();

        // Создание объекта субъекта (сервиса уведомлений)
        Subject notificationService = new NotificationService();

        // Добавление логирования к наблюдателям
        Observer emailNotifierWithLogging = new LoggingDecorator(emailNotifierForLogging);
        Observer smsNotifierWithLogging = new LoggingDecorator(smsNotifierForLogging);

        // Подключение логированных наблюдателей (уведомителей) к сервису уведомлений
        notificationService.attach(emailNotifierWithLogging);
        notificationService.attach(smsNotifierWithLogging);

        // Отправка уведомления с логированием
        notificationService.notifyObservers("Новое сообщение с логированием: тестовое уведомление");

        // Проверка, что уведомления были отправлены и логированы
        assertEquals("Отправка уведомления по Email: Логирование: Новое сообщение с логированием: тестовое уведомление",
                ((LoggingDecorator) emailNotifierWithLogging).getReceivedMessage());
        assertEquals("Отправка уведомления по SMS: Логирование: Новое сообщение с логированием: тестовое уведомление",
                ((LoggingDecorator) smsNotifierWithLogging).getReceivedMessage());
    }


}