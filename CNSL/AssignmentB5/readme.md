# How to run the chat app

Press the blue button underneath the code written below.
Once you see the terminal, write the following command and press enter:

```python3 server.py```

You have successfully started the server.

Now, to connect a client to the server, open another terminal and write:
cd usercode
then write

```python3 client.py -u Sherlock```

You have successfully connected a client named Sherlock to the server.

Sherlock is not going to talk to himself, therefore, let’s make another client named Watson:

`python3 client.py -u Watson`

To send the message from the client terminal, follow this format:

`msg {NameOfClient} {ActualMsg}`

For example, you can run this command in the terminal of Sherlock:

`msg Watson Education never ends, Watson. It is a series of lessons, with the greatest for the last.`

Have fun chatting!