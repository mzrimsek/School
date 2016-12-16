# Installation Instructions

1\. Create a cloud init script that will be used to bootstrap your Docket container  
2\. Create the container using the class [CLI tool](https://sysadmin1.cs.kent.edu/dostanle/cs43202api), passing in your cloud_init script  

```bash
pip install --upgrade git+https://sysadmin1.cs.kent.edu/dostanle/cs43202api.git  
cs43202cli container create --name SOMENAME --cloud-init /path/to/your/cloud-init.sh  

```     

3\. Wait a few minutes (to a while) for installation to complete  
4\. Make sure you can establish a connection to your container with Ansible  

```bash
cd ansible/  
ansible all -m ping  
``` 

5\. Once you've established you can connect to the container with your SSH key, run the Ansible playbook to deploy the application  

```bash
ansible-playbook final.yml  
```

6\. Once all tasks have completed, verify that the application has been deployed correctly  

```
ssh CONTAINER_IP_ADDRESS  
curl http://localhost  
curl http://localhost/quote/100  
```

