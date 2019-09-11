#instala selenium
pip install selenium
#faz o download do geckodriver
wget https://github.com/mozilla/geckodriver/releases/download/v0.25.0/geckodriver-v0.25.0-linux32.tar.gz
#extrai o download
tar -xvzf geckodriver-v0.25.0-linux32.tar.gz geckodriver
#torna o bin executavel
chmod +x geckodriver
#move pra o diretorio
sudo mv geckodriver /usr/local/bin/
