# security

## 鉴权

### JWT

<img src="https://pic1.zhimg.com/80/v2-7789057d5744891fdf3366d7887ab6e8_1440w.jpg" style="zoom:80%;" />

#### secure JWT

[What Happens If Your JWT Is Stolen?](https://developer.okta.com/blog/2018/06/20/what-happens-if-your-jwt-is-stolen)

JWT best practices:

1. Give tokens an expiration

    用两种token：ACCESS_TOKEN和REFRESH_TOKEN

2. Embrace HTTPS

3. Do not add sensitive data to the payload

#### session VS JWT

无状态和可扩展性：Tokens存储在客户端。完全无状态，可扩展。我们的负载均衡器可以将用户传递到任意服务器，因为在任何地方都没有状态或会话信息。

安全：Token不是Cookie。（The token, not a cookie.）每次请求的时候Token都会被发送。而且，由于没有Cookie被发送，还有助于防止CSRF攻击。即使在你的实现中将token存储到客户端的Cookie中，这个Cookie也只是一种存储机制，而非身份认证机制。

Session方式存储用户信息还有一个问题在于要占用大量服务器内存，增加服务器的开销。

#### secure cookie

1. Data sent **over SSL (HTTPS)** is fully encrypted, headers included (hence cookies), only the Host you are sending the request to is not encrypted. It also means that the GET request is encrypted (the rest of the URL).
2. Although an attacker could force a client to respond over HTTP, so it is highly recommended to **use the "Secure" flag in your cookie**, which enforce the use of HTTPS to send cookies.
3. Also, using **the flag HTTPOnly** would greatly enhance the security of your site since it does not allow Cookies to be read with Javascript code (Mitigating potential XSS vulnerabilities).

## HTTPS

> HTTPS = HTTP + SSL
>
> SSL = secure sockets Layer

<img src="./note_img/https_illustrate.png" style="zoom:80%;" />

**HTTPS在传输的过程中会涉及到三个密钥：**

服务器端的公钥和私钥，用来进行非对称加密

客户端生成的随机密钥，用来进行对称加密

一个HTTPS请求实际上包含了两次HTTP传输，可以细分为8步。

1. 客户端向服务器发起HTTPS请求，连接到服务器的443端口

2. 服务器端有一个密钥对，即公钥和私钥，是用来进行非对称加密使用的，服务器端保存着私钥，不能将其泄露，公钥可以发送给任何人。

3. 服务器将自己的公钥发送给客户端。

4. 客户端收到服务器端的证书之后，会对证书进行检查，验证其合法性，如果发现发现证书有问题，那么HTTPS传输就无法继续。严格的说，这里应该是验证服务器发送的数字证书的合法性，关于客户端如何验证数字证书的合法性，下文会进行说明。如果公钥合格，那么客户端会生成一个随机值，这个随机值就是用于进行对称加密的密钥，我们将该密钥称之为client key，即客户端密钥，这样在概念上和服务器端的密钥容易进行区分。然后用服务器的公钥对客户端密钥进行非对称加密，这样客户端密钥就变成密文了，至此，HTTPS中的第一次HTTP请求结束。

5. 客户端会发起HTTPS中的第二个HTTP请求，将加密之后的客户端密钥发送给服务器。

6. 服务器接收到客户端发来的密文之后，会用自己的私钥对其进行非对称解密，解密之后的明文就是客户端密钥，然后用客户端密钥对数据进行对称加密，这样数据就变成了密文。

7. 然后服务器将加密后的密文发送给客户端。

8. 客户端收到服务器发送来的密文，用客户端密钥对其进行对称解密，得到服务器发送的数据。这样HTTPS中的第二个HTTP请求结束，整个HTTPS传输完成。

## spring security

message digest消息摘要

SHA1将任意长度数据转换成一个160bits的序列（20bytes）（若更改一个bit生成的序列会产生很大变化）

message digest算法public known

公钥秘钥对

私钥加密（本身无法解密）公钥可以解密，公钥秘钥无法互推

用私钥将摘要加密 -> 公钥可以解密 -> 篡改后无法再次加密（用公钥无法解开，得知篡改）

公钥秘钥分发

![image-20211018164547236](/Users/weixinpeng/Library/Application Support/typora-user-images/image-20211018164547236.png)

A -> info(digest) -> B

info使用B的公钥加密

<img src="/Users/weixinpeng/Library/Application Support/typora-user-images/image-20211018165952670.png" alt="image-20211018165952670" style="zoom:50%;" />

Friend用自己的私钥对公钥签名，You拿Friend的公钥解开。和收到的公钥对比，一致则接受。

<img src="/Users/weixinpeng/Library/Application Support/typora-user-images/image-20211018170517088.png" alt="image-20211018170517088" style="zoom:80%;" />

<img src="/Users/weixinpeng/Library/Application Support/typora-user-images/image-20211018171749301.png" alt="image-20211018171749301" style="zoom:80%;" />

对称加密：性能高

非对称加密：速度慢，安全。

先用非对称传对称秘钥，之后使用对称秘钥通信。

## SSO

> single sign on

Kerberos prorocol

cons:

单一故障节点（AS/TGS崩了整个系统就挂了）solution：分布式

时钟不一致 ——> 设置时钟差异阈值

## SQL注入

不要字符串拼接

statement X

prepared statement √

in JDBC

## 跨站脚本攻击

- rich text
- 过滤

## DDoS

