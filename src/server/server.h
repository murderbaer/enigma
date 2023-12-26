enum HTTP_REQUEST_HEADER {
    HTTP_ACCEPT,
    HTTP_ACCEPT_ENCODING,
    HTTP_CONNECTION,
    HTTP_COOKIE,
    HTTP_CONTENT_TYPE,
    HTTP_CONTENT_LENGTH,
    HTTP_USER_AGENT,
    HTTP_HOST,
    HTTP_METHOD,
    HTTP_PATH,
    HTTP_VERSION,
    HTTP_BODY,
};

char *http_request_header_str[] = {
    "Accept",
    "Accept-Encoding",
    "Connection",
    "Cookie",
    "Content-Type",
    "Content-Length",
    "User-Agent",
    "Host",
    "Method",
    "Path",
    "Version",
    "Body",
};



typedef struct Request {
    char *method;
    char *path;
    char *version;
    char *host;
    char *user_agent;
    char *accept;
    char *accept_encoding;
    char *connection;
    char *cookie;
    char *content_type;
    char *content_length;
    char *body;
} Request;

int server_run(void);
