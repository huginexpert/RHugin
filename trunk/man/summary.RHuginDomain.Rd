\name{summary.RHuginDomain}
\alias{summary.RHuginDomain}

\title{RHuginDomain Summary Method}

\description{
Summary method for RHugin domain objects.
}

\usage{
\method{summary}{RHuginDomain}(object, nodes, ...)
}

\arguments{
  \item{object}{an RHugin domain object.}
  \item{nodes}{optional, a character vector containing the names of one or more nodes in \code{object}. If given, the summary is only generated for the specified nodes. If \code{nodes} is missing, the summary is generated for all the nodes in \code{object}.}
  \item{\dots}{additional arguments are ignored.}
}

\value{
  a list with class \code{summary.RHuginDomain}. The list has one named element for each node in the RHuginDomain \code{object} (unless \code{nodes} was given). Each element is in turn a list containing the category, kind and subtype of the corresponding node.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\keyword{methods}


