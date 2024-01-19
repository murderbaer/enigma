FROM oven/bun:slim 

RUN apt-get update && apt-get install -y \
    nginx \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN bun install && \
    bun run build

COPY ./nginx.conf /etc/nginx/nginx.conf

RUN mkdir -p /var/www/html && \
    cp -r /app/dist/* /var/www/html

EXPOSE 8080

CMD ["nginx", "-g", "daemon off;"]


