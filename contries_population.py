from bs4 import BeautifulSoup
from csv import writer
import requests
import time
import smtplib
from email.message import EmailMessage

def send_email(country_data):
    email_send = ''  # Replace with your email
    email_receive = ''  # Replace with recipient's email
    app_password = ''  # Replace with the app password

    subject = 'New Job Postings'
    
    message = f"Subject: {subject}\n\n"
    message += "Here are some of the latest job postings:\n\n"  

    
    # Create an EmailMessage object
    msg = EmailMessage()
    msg.set_content(message)
    msg['Subject'] = subject
    msg['From'] = email_send
    msg['To'] = email_receive
    
    # Attach the jobs.csv file
    with open('world_population.csv', 'rb') as f:
        msg.add_attachment(f.read(), maintype='application', subtype='csv', filename='jobs.csv')

    server = smtplib.SMTP('smtp.gmail.com', 587)
    server.starttls()
    server.login(email_send, app_password)

    server.send_message(msg)
    server.quit()
    print('Email has been sent.')

def scrape_world_population():
    try:
        url = 'https://www.worldometers.info/world-population/population-by-country/'
        headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3'}
        page = requests.get(url, timeout=30, headers=headers)

        
        soup = BeautifulSoup(page.content, "html.parser")

        data_table = soup.find('table', id='example2')  # Update with the actual table ID or class

        if data_table:
            rows = data_table.find_all('tr')[1:]  # Skip the header row

            country_data = []

            with open('world_population.csv', 'w', encoding='utf8', newline='') as f:
                thewriter = writer(f)
                header = ['Rank', 'Country', 'Population', 'Yearly Change', 'Density (P/km2)', 'Land Area (Km2)', 'Median Age', 'Urban Population', 'World Share']
                thewriter.writerow(header)

                for row in rows:
                    columns = row.find_all('td')

                    if len(columns) >= 9:  # Adjust this to the correct number of columns
                        rank = columns[0].text.strip()
                        country = columns[1].text.strip()
                        population = columns[2].text.strip()
                        yearly_change = columns[3].text.strip()
                        density = columns[5].text.strip()
                        land_area = columns[6].text.strip()
                        med_age = columns[9].text.strip()
                        urban_pop = columns[10].text.strip()
                        world_change = columns[11].text.strip()

                        info = [rank, country, population, yearly_change, density, land_area, med_age, urban_pop,world_change]
                        thewriter.writerow(info)

                        job_info = {
                            'rank': rank,
                            'country': country,
                            'population': population,
                            'yearly_change': yearly_change,
                            'density': density,
                            'land_area': land_area,
                            'med_age': med_age,
                            'urban_pop':urban_pop,
                            'world_change': world_change
                        }

                        country_data.append(job_info)
        else:
            print("Data table not found.")
            return  # Return early if data table is not found

        send_email(country_data)  # Pass the scraped data to the email function
            
    except Exception as e:
        print(f"An error occurred during scraping: {e}")

if __name__ == '__main__':
    while True:
        scrape_world_population()
        wait_time = 10  # Sleep for 10 seconds
        print(f'Waiting {wait_time} seconds')
        time.sleep(wait_time)
