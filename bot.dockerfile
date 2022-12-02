FROM baduit/yololtranslator-core

RUN apt install python3 -y
RUN apt install python3-pip -y
RUN pip install discord

WORKDIR /yololtranslator/

# When running the container, make a -v path/on/host:/yololtranslator/secret_file
CMD ["python3", "discord_bot.py", "secret_file"]