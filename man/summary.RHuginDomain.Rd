\name{summary.RHuginDomain}
\alias{summary.RHuginDomain}

\title{RHuginDomain Summary Method}

\description{
Summary method for RHugin domain objects.
}

\usage{
\method{summary}{RHuginDomain}(object, nodes = FALSE, ...)
}

\arguments{
  \item{object}{an RHugin domain object.}
  \item{nodes}{a logical value or a character vector containing the names of one or more nodes in \code{object}.  The default value \code{FALSE} skips the node summary.  Alternatively, \code{TRUE} causes a summary to be computed for all nodes in \code{object}.}
  \item{\dots}{additional arguments are ignored.}
}

\value{
a list with class \code{summary.RHuginDomain}.

\item{node.names}{a character vector containing the names of the nodes in \code{object}.}

\item{edge.list}{a list describing the edges in \code{object}.  See \code{\link{get.edges}} for details.}

\item{domain}{a list containing the following elements:
  \describe{
    \item{compiled}{a logical value indicating whether \code{object} is compiled.}
    \item{equilibrium}{a character string, either \dQuote{sum} or \dQuote{max}, indicating the type of equilibrium used in the most recent propagation.}
    \item{evidence.mode}{a character vector with elements \dQuote{normal} and/or \dQuote{fast} indicating the evidence incorporation modes that could have generated the current equilibrium.  If no evidence has been incorporated then there is no difference between the equilibrium produced by a \dQuote{normal} propagation and the equilibrium produced by a \dQuote{fast-retraction} propagation.  In this case, \sQuote{evidence.mode} will list both possible modes.}
    \item{evidence.propagated}{a logical value, \code{TRUE} if \code{object} has evidence propagated.}
    \item{L.evidence.propagated}{a logical value, \code{TRUE} if \code{object} has likelihood evidence propagated.}
    \item{GC.evidence.propagated}{a logical value, \code{TRUE} if \code{object} has conditional Gaussian evidence propagated.}
    \item{evidence.to.propagate}{a logical value, \code{TRUE} if any evidence has been entered since the last propagation.}
    \item{tables.to.propagate}{a logical value, \code{TRUE} if any table data has changed since the last propagation.}
  }
}

\item{nodes}{the presence of this element depends on the value of \code{nodes} in the call.  A list whose elements are in turn lists containing the category, kind, subtype and (if applicable) states of the nodes specified in \code{nodes}.}
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\keyword{methods}


