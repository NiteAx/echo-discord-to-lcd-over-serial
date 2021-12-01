import discord
import serial
from dotenv import load_dotenv
import os

load_dotenv()

ignoreduserIDs = [773986530695839764, 349942347905236992] #Ignore users with these IDs
ignoredserverIDs = [495402640461660170]

ser = serial.Serial('COM4', 115200) 
print(ser.name)

client = discord.Client()

@client.event
async def on_ready():
    print('We have logged in as {0.user}'.format(client))

@client.event
async def on_message(message):
    if message.guild.id in ignoredserverIDs:
        return
    if message.author.id in ignoreduserIDs:
        return
    payload = message.author.name+": "+message.content
    print(payload)
    ser.write((payload+'\n').encode('utf-8'))

client.run(os.getenv("TOKEN"))