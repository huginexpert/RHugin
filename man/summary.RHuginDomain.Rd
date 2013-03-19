\name{summary.RHuginDomain}
\alias{summary.RHuginDomain}

\title{RHuginDomain Summary Method}

\description{
Summary method for RHugin domains.
}

\usage{
\method{summary}{RHuginDomain}(object, domain = TRUE, nodes = FALSE, jt = FALSE, ...)
}

\arguments{
  \item{object}{an RHugin domain.}
  \item{domain}{a logical value indicating whether a summary of the domain should be computed.}
  \item{nodes}{a logical value or a character vector containing the names of one or more nodes in \code{object}.  The default value \code{FALSE} skips the node summary.  Alternatively, \code{TRUE} causes a summary to be computed for all nodes in \code{object}.}
  \item{jt}{a logical value indicating whether a summary of the junction tree(s) should be computed.}
  \item{\dots}{additional arguments are ignored.}
}

\value{
a list with class \code{summary.RHuginDomain} containing the following elements.

\item{domain}{a list containing:
  \describe{
    \item{logfile}{a character string containing the file name of an open log file connection.  If there is no open log file then \code{logfile} is \code{NULL}.}
    \item{triangulated}{a logical value indicating whether \code{object} is triangulated.}
    \item{compiled}{a logical value indicating whether \code{object} is compiled.}
    \item{compressed}{a logical value indicating whether \code{object} is compressed.}
    \item{evidence.propagated}{a logical value, \code{TRUE} if \code{object} has evidence propagated.}
    \item{equilibrium}{a character string, either \dQuote{sum} or \dQuote{max}, indicating the type of equilibrium used in the most recent propagation.}
    \item{evidence.mode}{a character vector with elements \dQuote{normal} and/or \dQuote{fast} indicating the evidence incorporation modes that could have generated the current equilibrium.  If no evidence has been incorporated then there is no difference between the equilibrium produced by a \dQuote{normal} propagation and the equilibrium produced by a \dQuote{fast-retraction} propagation.  In this case, \sQuote{evidence.mode} will list both possible modes.}
    \item{L.evidence.propagated}{a logical value, \code{TRUE} if \code{object} has likelihood evidence propagated.}
    \item{GC.evidence.propagated}{a logical value, \code{TRUE} if \code{object} has conditional Gaussian evidence propagated.}
    \item{evidence.to.propagate}{a logical value, \code{TRUE} if any evidence has been entered since the last propagation.}
    \item{tables.to.propagate}{a logical value, \code{TRUE} if any table data has changed since the last propagation.}
  }
}

\item{nodes}{a list of node summaries. Each node summary is a list with the following elements:
  \describe{
    \item{category}{a character string indicating the category of the node.}
    \item{kind}{a character string indicating the kind of the node.}
    \item{subtype}{a character string indicating the subtype of the node.}
    \item{states}{a vector listing the states of the node.}
    \item{model}{a logical value indicating whether the node has a model.}
    \item{model.size}{a single numeric value giving the number of configurations of the model's model nodes.}
    \item{size}{a single numeric value giving the size (i.e., the number of state configurations of discrete nodes represented in the table) of the node's table.}
    \item{cgsize}{a single numeric value giving the Conditional Gaussian size of the node's table.}
    \item{evidence.is.entered}{a logical value indicating whether evidence has been entered for the node.}
    \item{likelihood.is.entered}{a logical value indicating whether likelihood evidence has been entered for the node.}
    \item{evidence.is.propagated}{a logical value indicating whether evidence has been propagated for the node.}
    \item{likelihood.is.propagated}{a logical value indicating whether likelihood evidence has been propagated for the node.}
    \item{experience.table}{a logical value indicating whether the node has an experience table.}
    \item{fading.table}{a logical value indicating whether the node has an fading table.}
  }
}

\item{jt}{a list of junction tree summaries. Each junction tree summary is a list containing the following elements:
  \describe{
    \item{size}{a single numeric value giving the total number of discrete configurations of all clique and separator tables associated with the junction tree.}
    \item{cgsize}{a single numeric value giving the total number of Conditional Gaussian data elements in all tables in the junction tree.}
    \item{cliques}{a list containing the cliques comprising the junction tree.  Each clique is in turn a character vector containing the names of the nodes in the clique.}
  }
}

}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\keyword{methods}


