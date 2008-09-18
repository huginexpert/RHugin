\name{position.nodes}
\alias{position.nodes}

\title{Position Nodes}

\description{
Use R graphviz to compute a 2D layout of an RHugin domain and store the positions of the nodes in the RHugin domain object. 
}

\usage{
position.nodes(domain, nodes = NULL, layoutType = c("dot", "neato",
               "fdp", "manual", "none"), x, y)
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{nodes}{a character vector of node names in \sQuote{domain} whose positions will be set. If \code{NULL} positions are computed for all of the nodes.}
  \item{layoutType}{a character string specifying the layout engine Rgraphviz will use to position the nodes and edges in the plot.}
  \item{x}{if \code{layoutType == "manual"}, a vector of nonnegative integer values the same length as \sQuote{nodes} giving the x position of the nodes.}
  \item{y}{if \code{layoutType == "manual"}, a vector of nonnegative integer values the same length as \sQuote{nodes} giving the y position of the nodes.}
}

\details{
To retrieve the current position information from an RHugin domain use \code{layoutType == "none"}.
}

\value{
a matrix containing the x and y positions of the nodes.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\keyword{programming}


