\name{layoutRHugin}
\alias{layoutRHugin}

\title{Layout the Bayesian Network in an RHugin Domain Object.}

\description{
This function is intended to be used as the \code{layoutFun} argument in the \code{\link[Rgraphviz]{layoutGraph}} function the Rgraphviz package.  If the RHugin domain \code{domain} already contains layout information (for instance if \code{domain} was read from a .net or hkb file created with the Hugin GUI) then this information is used to generate the layout.  If no layout is present in \code{domain} then it is automatically created using Graphviz.  Additionally, the layout is stored in \code{domain}.
}

\usage{
layoutRHugin(x, domain, ...)
}

\arguments{
  \item{x}{a graphical representation of \code{domain}.  See \code{\link{as.graph.RHuginDomain}}.}
  \item{domain}{an RHugin domain.}
  \item{\dots}{additional arguments are ignored.}
}

\value{
\code{x} is returned with the layout information stored in the \code{renderInfo} slot.
}

\references{
\url{http://www.graphviz.org/}
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\examples{
library(Rgraphviz)

# Layout a bayesian network without calling plot.  The following
# example builds the ChestClinic network, uses the layoutRHugin
# function to add layout information then saves the domain as a net
# file.  Open "ChestClinic.net" using the Hugin GUI to see the layout.

demo("buildChestClinicNetwork", echo = FALSE)
layoutRHugin(x = as.graph.RHuginDomain(ChestClinic), domain = ChestClinic)
write.rhd(ChestClinic, file = "ChestClinic.net", type = "net") 
}

\keyword{programming}


