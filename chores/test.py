import requests

resp = requests.post('https://textbelt.com/text', {
    'phone': '8017074509',
    'message': 'Hello world',
    #'key': 'textbelt', # 1 text per day
    'key': '17f838d93caf1e7d7230afdf867d871c80cb5157BiJcgoCR72I26hofzhb5Th6t0',
    })
print(resp.json())
