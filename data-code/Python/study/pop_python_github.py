import requests
import pygal
from pygal.style import LightColorizedStyle as LCS, LightenStyle as LS


url = "https://api.github.com/search/repositories?q=language:python&sort=stars"
r = requests.get(url)
print("Status code", r.status_code)

response_dict = r.json()
print("Total repositories:", response_dict['total_count'])
names, plot_dicts = [], []
repo_dicts = response_dict['items']
for repo_dict in repo_dicts:
    names.append(repo_dict['name'])
    # stars.append(repo_dict['stargazers_count'])
    plot_dict = {
        'value': repo_dict['stargazers_count'],
        'label': str(repo_dict['description']),
        'xlink': repo_dict['html_url'],
    }
    plot_dicts.append(plot_dict)

my_style = LS('#333366', base_style=LCS)
chart = pygal.Bar(style=my_style, x_bale_rotation=45, show_legend=False)
chart.x_labels = names

#chart.add('', stars)
chart.add('', plot_dicts)
chart.render_to_file('C:\\Users\\ASUS\\Desktop\\python_repos.svg')
