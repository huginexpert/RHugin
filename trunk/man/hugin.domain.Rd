\name{hugin.domain}
\alias{hugin.domain}

\title{Create an RHugin Domain Object}

\description{
Create an RHugin domain.
}

\usage{
hugin.domain(graph, data)
}

\arguments{
  \item{graph}{an optional directed graph describing the structure of the domain.  See details.}
  \item{data}{an optional data frame.  See details.}
}

\details{
  When called without arguments, this function simply creates an empty domain.

  When only the \code{graph} argument is provided, a domain is created based on the structure of the graph. Each node in the graph becomes a discrete chance node in the domain (with the states left unspecified) and each edge in the graph becomes an edge in the domain.  A technical note: the \code{nodes} method is used to determine the set of nodes of \code{graph} and the \code{edges} method is used to determine the set of edges. Hence \code{graph} must be an object that supports both of these methods.

  When only the \code{data} argument is provided, the domain is populated with an initial set of discrete chance nodes.  The subtype of each node is determined by the class of the variable in the data frame: a numeric or integer variable results in a numbered node whose states are the sorted unique values of the variable, a logical variable results in a boolean node, and all other variables are coerced to factors and result in a labeled node with states equal to the levels of the factor.  If the data frame contains a variable named \dQuote{Freq} it will be ignored.  No edges are added to the domain.

  Finally, when both the \code{graph} and \code{data} arguments are provided, the structure of the domain is determined by \code{graph} (including the set of nodes).  Then the subtype and states for each node that corresponds to a variable in \code{data} are set as above.  Further, if data is provided for every node in the domain, then the conditional probability table (CPT) of each node is set using the appropriate marginalization of \code{data}.
}


\value{
an RHugin domain.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_new_domain}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
# Create an empty RHugin domain
hd <- hugin.domain()


# Create an RHugin domain from a graph
nodes <- c("Sat", "Infl", "Type", "Cont")
edgeL <- list(Sat = list(edges = numeric(0)),
              Infl = list(edges = 1),
              Type = list(edges = c(1, 4)),
              Cont = list(edges = 1))
g <- new("graphNEL", nodes, edgeL, "directed")
hd <- hugin.domain(graph = g)


# Create an RHugin domain using a data frame to generate initial nodes
library(MASS)
data(housing)
hd <- hugin.domain(data = housing)


# Create an RHugin domain from a graph and data
hd <- hugin.domain(graph = g, data = housing)
}

\keyword{programming}


