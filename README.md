Game of Cannon
By Ashish Gupta and Sanket Gandhi

## Description
The game description can be found [here](Description.pdf)
## Bot
The bot part uses Adversarial Search with Alpha-Beta pruning. The search was cut-off according to state analyzer function which decides depth of search for given state. A evaluation function was used to compare between different cut-off leaves.
## Key Points
For choosing next child node to explore we used same evaluation function so that maximum nodes are pruned. The state analyzer function was desgined in such way that at start of game the depth was high and as game progresses the depth decreases.
## Evaluation Function
Eval(state) = 100*so + 1000*to + 10*ct + at - 0.000001*dt <br />
where <br />
so = net soldier differencd <br />
to = net townhall differencd <br />
ct = net cannon difference <br />
at = net attacking positions difference <br />
dt = net difference of sum of distances of soldier from opponents townhall <br />
## Game Instance
![alt text](http://url/to/img.png)
