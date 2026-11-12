# build
FROM alpine:latest AS builder
WORKDIR /app

RUN apk add --no-cache build-base

COPY Makefile ./
COPY src ./src

RUN make

# run
FROM alpine:latest
WORKDIR /app

RUN apk add --no-cache ca-certificates libstdc++ libgcc

COPY --from=builder /app/build ./build

EXPOSE 1121
CMD ["./build/itch"]
