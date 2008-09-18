\name{plot.RHuginDomain}
\alias{plot.RHuginDomain}

\title{Plot an RHugin Domain}

\description{
Plot method for RHugin domain objects.
}

\usage{
\method{plot}{RHuginDomain}(x, y, layoutType = c("dot", "neato", "fdp"), ...)
}

\arguments{
  \item{x}{an RHugin domain object.}
  \item{y}{this argument is not used.}
  \item{layoutType}{a character string specifying the layout engine Rgraphviz will use to position the nodes and edges in the plot.}
  \item{\dots}{additional arguments are passed to the \sQuote{Ragraph} plot method.}
}

\details{
A 2D repesentation of the RHugin domain \sQuote{x} is computed by Rgraphviz and displayed on a graphics device.
}

\value{
the \sQuote{Ragraph} object created by Rgraphviz representing the RHugin domain is invisibly returned.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\keyword{hplot}


