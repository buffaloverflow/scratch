FROM ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive
ENV tz=America/New_York

RUN apt update #&& 
RUN apt upgrade -y #&& 
RUN apt install -y python3 python3-pip

RUN pip install beautifulsoup4 html5lib

WORKDIR /app
COPY dl.py dl.py


