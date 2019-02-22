import smtplib
import time
import imaplib
import email

# -------------------------------------------------
#
# Utility to read email from Gmail Using Python
#
# ------------------------------------------------

def read_email_from_gmail():
    print "Beginning"
    try:
        mail = imaplib.IMAP4_SSL(SMTP_SERVER)
        mail.login(FROM_EMAIL,FROM_PWD)
        print "Logged In"
        mail.select('inbox')

        typ, data = mail.search(None, 'ALL')
        mail_ids = data[0]

        id_list = mail_ids.split()   
        first_email_id = int(id_list[0])
        latest_email_id = int(id_list[-1])


        for i in range(latest_email_id,first_email_id, -1):
            typ, data = mail.fetch(i, '(RFC822)' )

            for response_part in data:
                if isinstance(response_part, tuple):
                    msg = email.message_from_string(response_part[1])
                    email_subject = msg['subject']
                    email_from = msg['from']
                    if "msuanounce@morgan.edu" in email_from.lower():
                        if msg.is_multipart():
                            for payload in msg.get_payload():
                                # if payload.is_multipart(): ...
                                print(payload.get_payload())
                        else:
                            print msg.get_payload()
                        print 'From : ' + email_from + '\n'
                        print 'Subject : ' + email_subject + '\n'

    except Exception, e:
        print str(e)
ORG_EMAIL   = "@morgan.edu"
FROM_EMAIL  = "niwal7" + ORG_EMAIL
FROM_PWD    = str(raw_input("password\n"))
SMTP_SERVER = "imap.gmail.com"
SMTP_PORT   = 993
read_email_from_gmail()