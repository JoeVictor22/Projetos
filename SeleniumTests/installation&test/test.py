from selenium import webdriver

firefox = webdriver.Firefox()
firefox.get('https://diariodonordeste.verdesmares.com.br/')

posts = firefox.find_elements_by_class_name('c-teaser__inner')

for post in posts:
    post_title = post.find_element_by_class_name('c-teaser__heading  ')
    post_link = post.find_element_by_class_name('c-teaser__link')
    post_link = post_link.get_attribute('href')    
    print u"Titulo: {titulo}\nLink: {link} \n".format(
      titulo=post_title.text, link = post_link
  )

firefox.quit()
