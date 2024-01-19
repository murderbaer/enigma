FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libcjson-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN cmake -B build 
RUN cmake --build build

EXPOSE 17576

CMD ["/app/build/enigma", "--server", "&" ]


