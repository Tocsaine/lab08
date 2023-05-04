FROM ubuntu:latest

WORKDIR /usr/src/app

COPY . .

RUN apt-get update && apt-get install -y build-essential && \
    apt-get install -y g++ && \
    apt-get install -y libboost-all-dev && g++ -o client client.cpp

CMD ["./client"]

EXPOSE 80
