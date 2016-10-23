#LogServer & LogClient
- 一个基于Windows Pipe的Log写入的服务端以及客户端，避免多个客户端同时访问一个Log文件而导致的写入失败
- 这是将Log全部通过Windows Pipe传到服务端，由服务端统一写入文件