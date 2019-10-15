
# ==================================================================
# EC2
# My AMI 
save my instance config, on S3

# Market place 
pays as you go software

# Step3 Conifig
# user data
# advanced details user data , excute once when instance launched first time

# Step5 Add tags
key value pair to manage resources
e.g. run instance automatically using key and value to retrive the instance
employee, scan trigger lambda and use key value pair to start the employee instance

# rescale
once instance run cna terminate and action change the instance type to scale 
the instance
Action create image , will create a clone of the chosen instance

# s3 is a object storage(e.g. retrive storage by http request) while EBS is a block storage deveice
EBS storage needs to be in the same AZ
can create a snapshot of the EBS stored in S3(across in the zone)
copy over to the other EBS


# ==================================================================
# S3
# object based storage there is no need to formate the file
# each object will have a unit

# s3 can increase its volumen dynamically and each object in s3
# can be set different permission for access

# aws command line
# copy from local machine to the s3 storage
aws s3 cp demo.txt s3://my-bucket-name/hello.txt

# will sync my local folder to the s3 
aws s3 sync my_local_folder s3://my-bucket-name/files

# if a EC2 has permission to vis s3 it can access its content
# download file onto ec2 instance from the s3
aws s3 ls s3://my-bucket-name --recursive # list all files on the s3
aws s3 cp s3://my-bucket-name/hello.txt .

# ==================================================================
# Networking

# ==================================================================
# user groups
Create IAM user
create a user to restrict access to the EC2 instance

policies: # can be assigned to user , group and IAM roles
    -effect: allow
    -action:"get object"
    -recourse:s3/bucket

IAM role: 
-to give temperory policy for permissions to a user
-role can be given to recourses as well # e.g. ec2 instance get role to access to s3

# cloud trail
log your activities on aws for 90 days by default

# ==================================================================
# RDS

# ==================================================================
cloud practitioner certification book exame online

cloud guru
linux acadamy # certificate training

# ==================================================================

