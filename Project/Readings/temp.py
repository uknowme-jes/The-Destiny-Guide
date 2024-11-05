accound_sid = 'ACe22d19a1b843184e26fb60bfca3df002'
auth_token = '57563c30214019acea5949086b0b31d7'

twolio_number = '+12199405302'
target_number = '+918171911133'

from twilio.rest import Client

def send_sms():
    client = Client(accound_sid, auth_token)
    message = client.messages.create(
        body= "Hello! I am a hacker",
        from_=twolio_number,
        to=target_number
    )
    print(message)
send_sms()