FROM baduit/yololtranslator-core

RUN apt install python3 -y
RUN apt install python3-pip -y
RUN pip install "fastapi[all]"
RUN pip install fastapi_utils
RUN pip install "uvicorn[standard]"

WORKDIR /yololtranslator/
CMD ["uvicorn", "web_server:app", "--host", "0.0.0.0", "--port", "4910"]

EXPOSE 4910