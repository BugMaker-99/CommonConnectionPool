# CommonConnectionPool

MySQL数据库连接池，其中ConnectionPool类以单例模式进行设计，连接的生产和消费采用生产者-消费者模型，使用线程间的同步通信机制(条件变量和互斥锁)，避免每次访问数据库都需要创建连接，并连接数据库，大大提高了MySQL访问效率，
