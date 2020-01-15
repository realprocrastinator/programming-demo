
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
# RDS Mutiple A-Z Read Replicas and back up
# Automated Backups
> Automated backup can recover data to any points within a retention period(one or 35 days).
It will take a full daily snapshot and will store transaction logs throughout the day.
When recover aws would choose the most recent daily backup and then apply the transaction logs
relevant to that day.
> Automated Backups are enabled by default. The backup data is stored in S3 and will get free
storage space equal to the size of the the database1kjkj
> Backups are taken within a defined window, during the backup window , the storage IO may be 
suspeneded while your data is being backed up and might experience elevated latency.

# snapshot
> user initiated, peresistent even after the original RDS was deleted

# Restoring Backups
> when restoring a backup or snapshot, the database will be a new RDS instance with a new 
DNS endpoint

# Encyrption
> Encyrption is done using the Aws Key Management Service
if the original databse is encrypted ,same as the back up snapshot
and its replicas.
> Encrypting an existing DB instance is not supported,have to first
create a snapshot, make a copy of the snapshot and encrypt the copy.

# Multi-AZ RDS(synchrous)
> A copy of your production database in another availability zone. write to the primary DB
will automatically updated to the copy.
> In the event of primary DB failure, Amazon RDS will automatically failover to the standby
> It is only for disaster recover , not for performance, if need performance improvement, 
need Read Replicas.

# Read Replica
> read only copy of the primary database.Achieved by asynchronous replication from the
primary RDS instance to the read replica. Use for read heavy databse workload.
> available for MySQL Sever, PostgreSQL, MariaDB, Aurora.
> used for scaling ,not for data recovering.
> must have a automatic backups turned on in order to deploy a read replica.
> can have up to 5 read replica copies of any database.
> can have read replica of read replica.
> each read replica will have its own DNS endpoint.
> read replicas can have Multi-AZ.
> can create read replicas of Multi-AZ source database.
> read replicas can be promoted to be their own database. This would break the replication.
> read replica can be in a different region.


# ==================================================================
# ElasticCache
> improves the performance of the web by allowing to retrive information from fast , managed,
in memory caches, instead of relying entirely on the slow disk IO.

# Memcached:
> A widely adopted memory object caching system. ElasticCache is protocol compilant with 
memcahced.Popular tools with existing Memcahced environment is also compatible with the service.
> pure caching solution with no persistence, ElasticCache manages Memchaced nodes as a pool
that can grow and shrink, similar to an Amazon EC2 Auto Scaling Group. Individual nodes are
expendable, and ElastiCache provides additional capabilities here, such as automatic node
replacement and Auto Discovery.
# use case
> object caching is the primary goal, to offload the database.
> simple cahcing model.
> runing large cache nodes and require multithread performance with untilization of mutiple cores. 
> scale cache horizontally as you grow.

# Redis:
> open source key value store that support data structure like sorted sets, and lists.
ElasticCache supports Master/Slave replication and Multi-AZ which can be used to
achieve cross AZ redundancy.
> because of the replication and peresistent features of Redis, ElasticCache manages Redis
More as a relational database. Redis ElasticCache clusters are mananaged as stateful entities
taht include failover, similar to how Amazon RDS manages database failover.
# use case
> more advanced data types like lists, hashes and sets.
> sorting and ranking dataset in memory like leaderboards.
> want to run in multiple AWS Availability Zone.

-summary
> ElasticCache is good if DB is read-heavy and not prone to frequent changing
> if just to take of the load of the DB can simply use Memcahced
> if do some analysis then choose Redshift. 
# use Memcahced
> object caching is the primary goal
> keep things as simple as possible
> scale cache horizontally
# use Redis
> hae advanced datatype like lists, hashes and sets
> doing data sorting, ranking
> Data Persistence
> Muti AZ
> Pub/Sub capabilities

# ==================================================================
# S3
> secure and scalable object storage that can be access from anywhere


aws s3 cp local_source_dir  s3://prokopto.info/local_source_dir --recursive # include the dir
aws s3 cp local_source_dir  s3://prokopto.info --recursive # only the content in the dir copy
aws s3 ls s3://prokopto.info
aws s3 rm s3://prokopto.info # remove all content in the bucket
aws s3 sync local_source_dir s3://prokopto.info # remove all content in the bucket




