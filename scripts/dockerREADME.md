## Docker Usage


#### docker_deploy_local.sh

Purpose: Builds binary from dream-team root directory and deploys binary 
to './deploy' directory. <br />
Usage: './scripts/docker_deploy_local.sh' <br />
Notes: give executable permission on setup 'chmode u+x docker_deploy_local.sh' <br />


#### docker_run_deployed_server.sh

Purpose: Runs the binary ('./deploy/bin/webserver') with config_file and 
contents from 'deploy' directory <br />
Usage: './scripts/docker_deploy_local.sh' <br />
Notes: give executable permission on setup 'chmode u+x docker_run_deployed_server.sh' <br />


#### docker kill commands

Purpose: Kills a docker container to free port and allow 'docker_run_deployed_server.sh'
to run again <br />
Usage: docker ps <br />
docker kill `<process id>` <br />
