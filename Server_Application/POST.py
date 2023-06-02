import requests

url = 'http://127.0.0.1:8080'
data = {'key1': 'value1', 'key2': 'value2'}
response = requests.post(url, data=data)

print(response.text)