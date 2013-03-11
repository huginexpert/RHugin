\name{compile.RHuginDomain}
\alias{compile}
\alias{compile.RHuginDomain}

\title{Compile an RHugin Domain}

\description{
Compile an RHugin domain using the default triangulation method (unless the domain has already been triangulated).  The domain must contain at least one chance or decision node.
}

\usage{
compile(object, ...)
\method{compile}{RHuginDomain}(object, save = FALSE, approximate = NULL, ...)
}

\arguments{
  \item{object}{an RHugin domain.}
  \item{save}{a logical value.  If \code{TRUE} then copies of the initial belief and junction tree tables of \code{domain} are stored in memory.}
  \item{approximate}{a positive numeric value giving the \eqn{\epsilon} use to approximate the domain. If \code{NULL}, no approximation is done (the default - see details).}
  \item{\dots}{additional arguments are ignored.}
}

\details{
Compiling a domain with \code{save = TRUE} approximately doubles its memory consumption.  However, calls to \code{\link{initialize.domain}} will be significantly faster since the tables can be read from memory rather than recomputed.  A memory backup is automatically kept up-to-date (for example, when a conditional probability table is modified).  The memory backup will be deleted as part of any uncompilation or compression operation.

Compiling a domain with \code{approximate} set to a positive value \eqn{\epsilon} causes the domain to be approximated. The approximation technique implemented in Hugin is based on the assumption that very small probabilities in the probability distribution reflect (combinations of) events that rarely occur in practice. Approximation is the process of setting all such near-zero probabilities to zero. The primary objective of this process is to minimize storage consumption through compression.

It should be emphasized that this approximation technique should only be used when one is not interested in the probabilities of unlikely states. The relative error -- although small in absolute terms -- for such probabilities can be huge. Approximation should be used only if all one is interested in is to identify the most probable state(s) for each node given the evidence.

The effect of approximation is as follows: for each clique in domain, a value \eqn{\delta} is computed such that the sum of all elements less than \eqn{\delta} in (the discrete part of) the clique table is less than \eqn{\epsilon}. These elements are then set to 0. In effect, \eqn{\epsilon} specifies the maximum probability mass to remove from each clique.

Approximation can only be applied to ordinary belief networks (continuous nodes are allowed, but approximation only applies to configurations of the states of the discrete nodes).  The type of equilibrium on the junction trees of domain must be \emph{sum} incorporating all evidence (if any) in \emph{normal} mode.  RHugin automatically compresses (\code{\link{compress}}) the domain after approximation.

The function \code{\link{get.approximation.constant}} computes the probability mass of the remaining configurations.
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://download.hugin.com/webdocs/manuals/api-manual.pdf}: \code{h_domain_compile}, \code{h_domain_approximate} and \code{h_domain_save_to_memory}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\seealso{
  \code{\link{initialize.domain}}, \code{\link{compress}}, \code{\link{get.approximation.constant}}.
}

\examples{
demo("apple", echo = FALSE)

# Compile the domain
compile(apple)
}

\keyword{programming}


