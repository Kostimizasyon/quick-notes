# docker:::

Packages, version installing yada yada can take a lot of time to setup : solution => docker

Shit works on your system but not others => use docker to test

Consists of Three Main Parts:

Images => Your code / packages all that juicy stuff => os, dependencies etc. (Basically a read-only template)

Containers => The instance of the running image on your computer, dynamically allocate memory as needed (can scale infinitely in theory), they are stateless => all data lost inside when shut down, they are portable

DockerFile => Your recipe on how you should run the code / configure the application at hand => used to build our image

-----

Specifics:::

Docker Compose => Lets say you have databases, backend, frontend etc => You will have multiple containers each for that respective part of the app. 
Docker Compose lets us easily have these containers talk to each other, defined in a single `docker-compose.yml` file.

Docker Volume => basically a folder on your computer that docker uses to pass data between containers etc (also containers are temporary and volumes will give them permanent data, like saving your DB entries)

Docker Network => The invisible LAN cable. Lets your backend securely talk to your database without exposing the database to the whole internet.

Docker Hub / Registries => GitHub, but for Docker images. Where you pull official bases (Node, Python, Ubuntu) and push your own creations.

----

.dockerignore => Exactly like .gitignore. Stops massive/useless files (like `node_modules` or `.git`) from getting sucked into your image during build and making it bloated as hell.

DockerFile {
    FROM => usually the first line, import from a base image || FROM debian:bullseye
    WORKDIR => create and cd into a working directory || WORKDIR /usr/src
    RUN => CLI run commands (happens DURING the build process) || RUN apt-get install python3
    USER => by default we are the root user, but we can change that with this (good for security)
    COPY X Y => copy x(your local system) into Y (inside the container)
    ENV X=Y => set an environment variable
    EXPOSE X => expose port X (mostly for documentation, doesn't actually open the port to your localhost automatically)
    CMD ["python3", "-m", "http.server"] => commands to run when starting up a container # only ONE CMD per container
    ENTRYPOINT => passes arguments alongside the container run (makes your container act like a strict executable CLI tool)
    LABEL => adds metadata (author, version, description)
    HEALTHCHECK --interval=30s --timeout=10s:
        CMD curl -f google.com || exit 1
    VOLUME path => defining mount points for storing data
}

-----
cli (The Daily Drivers)

docker build -t my_app:v1 . => cook the recipe (Dockerfile in current dir '.') into an actual Image named 'my_app'
docker run -p 8080:80 image_name => spin up the container (binds your computer's port 8080 to the container's port 80)
docker run -d image_name => run the container detached (in the background so it doesn't hijack your terminal)

docker ps => wtf is currently running? (add -a to see dead/stopped containers too)
docker stop <id> => ask the container politely to shut down (graceful)
docker kill <id> => rip the power cord out (force stop)
docker rm <id> => nuke a dead container from your hard drive
docker rmi <id> => nuke the image itself to free up space

docker exec -it <id> bash => hack into the matrix (opens an interactive terminal INSIDE the running container)
docker logs <id> => wtf went wrong? spits out the terminal output/crash logs of the container

docker push => push your built image to a cloud service (Docker Hub, AWS ECR)
docker pull => pull an image down from the cloud

docker-compose up -d => spin up the whole orchestra (all containers in your yml) in the background
docker-compose down => kill the orchestra and automatically clean up the network mess
