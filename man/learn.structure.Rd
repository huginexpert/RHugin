\name{learn.structure}
\alias{learn.structure}

\title{Learn Network Structure}

\description{
Learn network structure using the PC algorithm.
}

\usage{
learn.structure(domain, alpha = 0.05, constraints = NULL)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{alpha}{a single numeric value specifying the significance level for rejecting the true independence hypothesis.}
  \item{constraints}{a list of constraints on the edges. See details.}
}

\details{
The current implementation of the PC algorithm in Hugin is limited to domains of discrete chance nodes. Any prior domain knowledge should be communicated to the learning algorithm via the constraints argument. This function will fail if any actual edges are present in the domain.  Additionally, a set of cases must be entered into the domain.

The constraints argument should be a list with two elements: \code{directed} and \code{undirected}.  Each of these elements should in turn be a list with two elements: \code{required} and \code{forbidden}.  The elements of these lists should be lists of length 2 character vectors containing node names (for example \code{c("A", "B")}).  The elements of \code{constraints$directed$required} indicate that an edge from \code{"A"} to \code{"B"} is required, the elements of \code{constraints$directed$forbidden} indicate that an edge from \code{"A"} to \code{"B"} is forbidden, the elements of \code{constraints$undirected$required} indicate that an edge between \code{"A"} and \code{"B"} is required but the learning algorithm is free to choose its direction and the elements of \code{constraints$undirected$forbidden} indicate that no edge may connect \code{"A"} and \code{"B"}.  If there are no constraints of a given type then the corresponding list should be set to \code{NULL}.  If there is no prior domain knowledge then \code{constraints} should be set to 'code{NULL} (this is the default setting). An example is provided below.
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_domain_learn_structure} and \code{h_domain_set_significance_level}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
\code{\link{set.cases}}.
}

\examples{
# Create an RHugin domain
apple <- hugin.domain()

# Add nodes
add.node(apple, "Sick", states = c("yes", "no"))
add.node(apple, "Dry", states = c("yes", "no"))
add.node(apple, "Loses", states = c("yes", "no"))
  
# Add cases
data(apple)
set.cases(apple, apple.cases)

learn.structure(apple)
plot(apple)


# Using domain knowledge
asia <- hugin.domain()

# Add nodes
nodes <- c("Asia", "Smoking", "Tuberculosis", "LungCancer",
            "Bronchitis", "Either", "XRay", "Dyspnoea")
for(node in nodes)
  add.node(asia, node, states = c("yes", "no"))

# Set cases
data(asia)
set.cases(asia, asia.cases)

# require a directed edge from Asia to Tuberculosis and from
# Smoking to LungCancer; forbid an edge from XRay to Asia.
directed.required <- list(c("Asia", "Tuberculosis"), c("Smoking", "LungCancer"))
directed.forbidden <- list(c("XRay", "Asia"))
directed <- list(required = directed.required, forbidden = directed.forbidden)

# require an edge between Smoking and Bronchitis;
# forbid an edge between LungCancer and Dyspnoea
undirected.required <- list(c("Smoking", "Bronchitis"))
undirected.forbidden <- list(c("LungCancer", "Dyspnoea"))
undirected <- list(required = undirected.required,
                   forbidden = undirected.forbidden)

# put into constraints list
domain.knowledge <- list(directed = directed, undirected = undirected)

learn.structure(asia, constraints = domain.knowledge)
plot(asia)
}

\keyword{programming}


