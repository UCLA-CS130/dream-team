#### Docker Usage


## docker_deploy_local.sh

Purpose: Builds binary from dream-team root directory and deploys binary 
to './deploy' directory.
Usage: './scripts/docker_deploy_local.sh'
Notes: give executable permission on setup 'chmode u+x docker_deploy_local.sh'


## docker_run_deployed_server.sh

Purpose: Runs the binary ('./deploy/bin/webserver') with config_file and 
contents from 'deploy' directory
Usage: './scripts/docker_deploy_local.sh'
Notes: give executable permission on setup 'chmode u+x docker_run_deployed_server.sh'


## docker kill commands

Purpose: Kills a docker container to free port and allow 'docker_run_deployed_server.sh'
to run again
Usage: docker ps
docker kill <process id>
