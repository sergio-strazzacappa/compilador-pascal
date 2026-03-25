FROM debian:trixie-slim

RUN apt-get update && apt-get install -y    \
    curl                                    \
    build-essential                         \
    && rm -rf /var/lib/apt/lists/*

RUN curl -fsSL https://opencode.ai/install | bash

WORKDIR /app
COPY . /app
