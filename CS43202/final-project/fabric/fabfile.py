from fabric.api import env, task, sudo, run
from cs43202api import Client

env.use_ssh_config = True

# Create a CS43202api client object and automatically get all container ips!
client = Client()
env.hosts = client.get_container_ips()

@task
def example():
    run('whoami')

@task
def yumupgrade():
    sudo('yum -y -q upgrade')

######
# The following task can be used after you deploy to verify the application
# is working as expected. It basically logs into the remote host and runs
# curl against a url that should return a specific quote. If this returns
# the expected quote, your deploy is probably good.
@task
def verifydeploy():
    run('curl -s http://127.0.0.1/quote/16')
