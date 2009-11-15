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
  \item{graph}{not implemented yet.  A DAG describing the structure of the belief network.}
  \item{data}{an optional data frame used to create an initial set of nodes for the domain.  Presently only discrete chance nodes are created.  The subtype of each node is determined by the class of the variable in the data frame: a numeric or integer variable results in a numbered node whose states are the sorted unique values of the variable, a logical variable results in a boolean node, and all other variables are coerced to factors and result in a labeled node with states equal to the levels of the factor.  If the data frame contains a variable named \dQuote{Freq} it will be ignored.}
}

\value{
an RHugin domain.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/API_Manuals/}: \code{h_new_domain}.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\examples{
# Create an empty RHugin domain
hd <- hugin.domain()

# Create an RHugin domain using a data frame to generate initial nodes
library(MASS)
data(housing)
hd <- hugin.domain(data = housing)
}

\keyword{programming}


